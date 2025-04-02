import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Please Enter 3 Arguments")
        sys.exit(1)

    # TODO: Read database file into a variable
    read_database = open(sys.argv[1])
    reader = csv.DictReader(read_database)
    str_sequence = reader.fieldnames[1:]
    dna_database = list(reader)

    # TODO: Read DNA sequence file into a variable

    read_sequence = open(sys.argv[2], "r")
    dna_sequence = read_sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    longest_runs = {}

    for str_seq in str_sequence:
        longest_runs[str_seq] = longest_match(dna_sequence, str_seq)

    # Check database for matching profiles
    for row in dna_database:
        is_match = True

        for str_seq in str_sequence:
            if int(row[str_seq]) != longest_runs[str_seq]:
                is_match = False
                break

        if is_match:
            print(row['name'])
            return

    print("No match")
    read_sequence.close()
    read_database.close()


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


main()
