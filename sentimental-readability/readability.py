
def main():

    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = letters / words * 100
    S = sentences / words * 100

    output = 0.0588 * L - 0.296 * S - 15.8
    final_output = round(output)

    if final_output < 1:
        print("Before Grade 1")

    if final_output >= 16:
        print("Grade 16+")

    if 15 >= final_output > 1:
        print(f"Grade {final_output}")


def count_letters(text):

    total_letter = 0
    for i in range(0, len(text), 1):
        if (text[i].isalpha()):
            total_letter += 1

    return total_letter


def count_words(word):

    spaces = 0
    for i in word:
        if i.isspace():
            spaces += 1
    spaces += 1
    return spaces


def count_sentences(sentences):

    half_punc = 0

    for i in sentences:
        if i in ['.', '!', '?']:
            half_punc += 1

    return half_punc


main()
