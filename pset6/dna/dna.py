"""
    Implement a program that identifies to whom a sequence of DNA belongs.
    $ python dna.py databases/large.csv sequences/5.txt
    Lavender

In practice, since analysts know on which chromosome and at which location in the DNA an STR will be found, they can localize their search to just a narrow
section of DNA. But we’ll ignore that detail for this problem.
Your task is to write a program that will take a sequence of DNA and a CSV file containing STR counts for a list of individuals and then output to whom
the DNA (most likely) belongs.

"""
from sys import argv
import csv


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    else:
        data = argv[1]  # data.csv
        dna = argv[2]  # sequence.txt

    file_obj = open(data, "r")
    reader = csv.reader(file_obj, delimiter=',')

    people = {}
    field_names_list = next(reader)
    for row in reader:
        people[row[0]] = {}
        for i in range(1, len(row)):
            for col in range(len(field_names_list)):
                people[row[0]][field_names_list[i]] = row[i]
                break

    with open(dna, 'r') as dna_file:
        dna_sequence = dna_file.read()

    # For each STR compute the longest run of consecutive repeats in the DNA sequence.
    sta_from_dna = {'AGATC': 0, 'TTTTTTCT': 0, 'AATG': 0, 'TCTAG': 0,
                    'GATA': 0, 'TATC': 0, 'GAAA': 0, 'TCTG': 0}  # Dict for storing counted sta
    for sta_title in sta_from_dna:
        # Saving STR count in data structure
        sta_from_dna[sta_title] = count_sta(dna_sequence, sta_title)

    # Compare the STR counts against each row in CSV file.
    # Compare sta_title in people{} with sta_title in sta_from_dna
    matched_sta = 0
    for name, sta in people.items():
        matched_sta = 0
        for sta_title, sta_value in sta.items():
            if sta_title in sta_from_dna:
                if int(people[name][sta_title]) == int(sta_from_dna[sta_title]):
                    matched_sta += 1
        if matched_sta == len(sta):
            print(name)  # Printing result
            break
    if matched_sta != len(sta):
        print("No match")


def count_sta(dna_sequence, sta_title):
    count = 0
    i = 0
    max_count = 0
    while i <= len(dna_sequence) - len(sta_title):
        if dna_sequence[i:i+len(sta_title)] == sta_title:
            count += 1
            i = i + len(sta_title)
            if max_count < count:
                max_count = count
        else:
            i += 1
            count = 0
    return max_count


if __name__ == "__main__":
    main()