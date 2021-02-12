# Greedy Algorithm - finds the optimal solution for the problem
# prompt user for an amount of change
# always use the largest coin possible (use algorithm)
# keep track of coins used
# print the final number of coins print(coins)

from cs50 import get_float


def main():
    amount = get_positive_float("Change owed: ")
    amount = round(amount*100)
    coins_used = 0
    if (amount >= 25):
        coins_used = amount // 25
        amount = amount % 25
        print("amount = ", amount)
        print("coins = ", coins_used)
    if (amount < 25 and amount >= 10):
        coins_used += amount // 10
        amount = amount % 10
        print("amount = ", amount)
        print("coins = ", coins_used)
    if (amount < 10 and amount >= 5):
        amount = amount % 5
        coins_used += 1
    if (amount < 5):
        coins_used += amount
    print(coins_used)


def get_positive_float(prompt):
    while True:
        n = get_float(prompt)
        if n > 0:
            break
    return n


if __name__ == "__main__":
    main()