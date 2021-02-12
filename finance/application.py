import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from datetime import datetime #my import
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    user_id=session['user_id']
   # Forget any user_id, but maintain flashed message if present
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        """session.clear()"""
        session["_flashes"] = flashes

    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM portfolios WHERE userid= :user_id", user_id=user_id)
    result = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)
    cash = float(result[0]['cash'])
    grandtotal = cash

    if not stocks: #if not exists (No stocks yet!)
        flash("No stocks yet!")
    else:
        #price = stocks[0]["price"]
        #shares=stocks[0]["shares"]
        #totalvalueofstocks = float(shares) * float(price)
        #display the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).
        for stock in stocks:
            symbol = str(stock["symbol"])
            shares = int(stock["shares"])
            quote = lookup(symbol)
            price = float(quote["price"])
            totalvalueofstocks = float(shares) * float(price)
            grandtotal += totalvalueofstocks

    return render_template("index.html", stocks=stocks, grandtotal=usd(grandtotal), cash=usd(cash))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        session["_flashes"] = flashes

    """Get stock quote."""
    if request.method == "POST":
        #Ensure the stock was submitted
        symbol=request.form.get("symbol")
        shares = request.form.get("shares")
        quote = lookup(symbol) # return a dictionary [name, price, symbol]
        #Ensure the stock is valid
        if not symbol or quote is None:
            flash("You must provide a stock.")
        elif not shares or not shares.isdigit() or int(shares) < 1:
            flash("Please enter the right number of shares.")
        else:
            #If stock is valid -> check if user can afford it
            shares = request.form.get("shares")
            price=quote["price"]
            name=quote["name"]
            totalvalueofstocks = float(shares) * float(price)
            user_id = session["user_id"]
            rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)
            cash = rows[0]["cash"]
            transacted = datetime.now()
            if totalvalueofstocks < cash:
                db.execute("INSERT INTO history (userid, symbol, shares, price, transacted) VALUES (:user_id, :symbol, :shares, :price, :transacted)",
            user_id=user_id, symbol=symbol, shares=shares, price=price, transacted=transacted)

                #Query portfolio to see if stock exists
                exists = db.execute("SELECT symbol FROM portfolios WHERE userid= :user_id AND symbol=:symbol", user_id=session['user_id'], symbol=symbol)

                if len(exists) != 1: #if not exists
                    db.execute("INSERT INTO portfolios (userid, symbol, name, shares, price) VALUES (:user_id, :symbol, :name, :shares, :price)",
                        user_id=user_id, symbol=symbol, name=name, shares=shares, price=price)
                    flash("The stock inserted into portfolio.")
                else:
                    share_user = db.execute("SELECT shares FROM portfolios WHERE userid= :user_id AND symbol=:symbol", user_id=session['user_id'], symbol=symbol)
                    shares = request.form.get("shares")
                    shares_update = float(share_user[0]["shares"]) + float(shares)
                    price=quote["price"]
                    db.execute("UPDATE portfolios SET price = :price, shares = :shares WHERE userid = :user_id AND symbol=:symbol",
                        user_id=user_id, price=price, shares=shares_update, symbol=symbol)
                    flash("The portfolio updated!")

                #Update cash stored in the users table
                db.execute("UPDATE users SET cash = cash - :totalvalueofstocks WHERE id = :user_id", user_id=user_id, totalvalueofstocks = totalvalueofstocks);

                flash("The stock is bought and added to history!")

                return redirect("/")
                #return render_template("index.html", cash=cash, totalcash=totalcash)
            else:
                flash("You don't have enough cash to buy this stocks.")
                return redirect("/buy")
        return redirect("/buy")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM history WHERE userid=:user_id", user_id = session["user_id"])
    if not stocks:
        flash("The stock is not exists.")
    return render_template("history.html", stocks = stocks)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id, but maintain flashed message if present
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        session.clear()
        session["_flashes"] = flashes
    else:
        # Forget any user_id
        session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            flash("Must provide username.")
            """return apology("must provide username", 403)"""
            return redirect("/")

        # Ensure password was submitted
        elif not request.form.get("password"):
            flash("Must provide password.")
            """return apology("must provide password", 403)"""
            return redirect("/")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            """return apology("invalid username and/or password", 403)"""
            flash("Invalid username and/or password.")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/managecash", methods=["GET", "POST"])
@login_required
def managecash():
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        session["_flashes"] = flashes

    """ Manage cash """
    if request.method == "POST":
        #Ensure the amount is valid
        amount = request.form.get("amount")
        if not amount:
            flash("You must provide an amount.")
        elif not amount or not amount.isdigit() or int(amount) < 1:
            flash("Please enter the right amount.")
        else:
            #Adding funds to the users table
            cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
            if not cash:
                flash("There is no cash on your account or there is an error happened.")
            else:
                amount = int(cash[0]["cash"]) + int(amount)
                db.execute("UPDATE users SET cash=:amount WHERE id=:user_id", amount=amount, user_id=session["user_id"])
            flash("The funds added!")
        return redirect("/managecash")
    else:
        cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
        if not cash:
            flash("There is no cash on your account or there is an error happened.")
        return render_template("cash.html",cash=cash[0]["cash"])
    return render_template("cash.html",cash=cash[0]["cash"])

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        session["_flashes"] = flashes

    """Get stock quote."""
    if request.method == "POST":
        #Ensure quote was submitted
        if not request.form.get("symbol"):
            flash("The stock was not entered.")
            return redirect("/quote")
        quote = lookup(request.form.get("symbol")) # return a dictionary [name, price, symbol]
        #Ensure the stock is valid
        if quote is None:
            flash("The stock is not valid.")
            return redirect("/quote")
        else:
            price = usd(quote["price"])
            return render_template("quoted.html", quote=quote, price=price)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            flash("Must provide username.")
            return redirect("/register")

        # Ensure password was submitted
        elif not request.form.get("password"):
            """return apology("must provide password", 403)"""
            flash("Must provide password.")
            return redirect("/register")

        # Query database for username
        username=request.form.get("username")
        rows = db.execute("SELECT * FROM users WHERE username = :username",username=username)

        # Ensure username exists and password is correct
        if len(rows) == 1:
            return apology("username exists, try different username", 403)

        password=request.form.get("password")
        confirmation=request.form.get("confirmation")

        if (password == confirmation):
            password = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashpswd)", username=username, hashpswd=password)
            rowid = db.execute("SELECT id FROM users WHERE username = :username", username=username)
            if len(rowid) != 1:
                return apology("some error happened, try more", 403)
            session["user_id"] = rowid[0]["id"]
            flash("Registration succeed.")
            return redirect("/")
        else:
            flash("Password do not match.")
            return redirect("/register")
        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id=session['user_id']
    if session.get("_flashes"):
        flashes = session.get("_flashes")
        session["_flashes"] = flashes
    """Sell shares of stock"""
    if request.method == "POST":
        #Ensure shares and stock was submitted

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        stock = db.execute("SELECT symbol, shares FROM portfolios WHERE userid = :user_id AND symbol=:symbol", user_id=user_id, symbol = symbol)
        quote = lookup(symbol) # return a dictionary [name, price, symbol]

        #Ensure the stock is valid
        if not symbol or quote is None:
            flash("You must provide a stock.")
        elif not shares or not shares.isdigit() or int(shares) < 1 or int(shares) > int(stock[0]["shares"]):
            flash("Please enter the right number of shares.")

        #If everything checked -> sale
        else:
            value = quote["price"] * int(shares)
            shares_update = int(stock[0]["shares"]) - int(shares)

            #If the user is selling all the stocks, remove stock from the portfolio
            if int(stock[0]["shares"]) == int(shares):
                db.execute("DELETE FROM portfolios WHERE userid = :user_id and symbol = :symbol",
                            user_id=user_id, symbol=symbol)
            # If the user is just selling some of the shares, update the portfolio
            elif int(stock[0]["shares"]) > int(shares):
                db.execute("UPDATE portfolios SET shares = :shares, price=:price WHERE userid = :user_id AND symbol=:symbol",
                    user_id=user_id, shares=shares_update, symbol=symbol, price=quote["price"])

            #Add the transaction to the user's history

            db.execute("INSERT INTO history (userid, symbol, shares, price, transacted) VALUES (:user_id, :symbol, :shares, :price, :transacted)",
            user_id=user_id, symbol=symbol, shares= int(shares) * -1, price=quote["price"], transacted = datetime.now())

            # Update the value of cash in users after the sale of stocks
            db.execute("UPDATE users SET cash = cash + :value WHERE id = :user_id", value=value, user_id=user_id)


            flash("The stock is sold!")
            return redirect("/") #Redirect user to the portfolio

        return redirect("/sell")
    else:
        """Show stocks in the HTML-select"""
        stocks = db.execute("SELECT symbol FROM portfolios WHERE userid= :user_id", user_id=user_id)
        if not stocks: #if not exists
            flash("There is no stocks to sell.")
        else:
            return render_template("sell.html", stocks=stocks)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
