from collections import defaultdict

def decode_substitute(cipher, key):
    print()
    plain = ""
    for i in cipher:
        plain += key[(ord(i) - ord("A"))]
    return plain

if __name__ == "__main__":
    cipher = input()
    freq = dict()
    for i in range(26):
        freq[chr(ord("A") + i)] = 0
    for i in cipher:
        freq[i] += 1
    freq = sorted(freq.keys(), reverse=True)
    # print(freq)
    # expected_freq = "EARIOTNSLCUDPMHGBFYWKVXZJQ"
    expected_freq = ['E', 'A', 'R', 'I', 'O', 'T', 'N', 'S', 'L', 'C', 'U', 'D', 'P', 'M', 'H', 'G', 'B', 'F', 'Y', 'W', 'K', 'V', 'X', 'Z', 'J', 'Q']
    expected_freq = "".join(expected_freq)

    mapping = {}
    for a,b in zip(expected_freq, freq):
        mapping[a] = b
    print( sorted(mapping.items(), key=lambda item: item[1]) )
    mapping = [('U', 'A'), ('J', 'B'), ('X', 'C'), ('C', 'D'), ('Z', 'E'), ('K', 'F'), ('E', 'G'), ('R', 'H'), ('A', 'I'), ('S', 'J'), ('N', 'K'), ('B', 'L'), ('F', 'M'), ('P', 'N'), ('O', 'O'), ('Q', 'P'), ('V', 'Q'), ('L', 'R'), ('H', 'S'), ('G', 'T'), ('M', 'U'), ('D', 'V'), ('Y', 'W'), ('I', 'X'), ('T', 'Y'), ('W', 'Z')]
    mapping = [item[1] for item in sorted(mapping, key=lambda item: item[0])]
    mapping = "".join(mapping)
    # print(mapping)
    # print("Cipher text:", cipher)
    print("Plain text:", decode_substitute(cipher, key=mapping))
    