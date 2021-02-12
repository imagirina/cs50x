from cs50 import get_string
from sys import argv


def main():
    if len(argv) != 2:
        exit("Usage: python bleep.py dictionary")  # sys.exit(1)
    filename = argv[1]
    print("What message would you like to censor?")
    plaintext = get_string("").split(" ")

    banned_words = set()
    file = open(filename, "r")
    for line in file:
        banned_words.add(line.strip())
    # check to see if any of the words match any of the words in banned list
    for word in plaintext:
        bipped = False
        for ban_word in banned_words:
            if word.lower() == ban_word:
                bipped = True
                for ch in word:
                    print('*', end="")
                print(" ", end="")
        if (bipped == False):
            print(word, end=" ")
    print()
    file.close()


if __name__ == "__main__":
    main()