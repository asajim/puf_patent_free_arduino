from __future__ import print_function
from collections import Counter
import distance

_xormap = {('0', '1'): '1', ('1', '0'): '1', ('1', '1'): '0', ('0', '0'): '0'}


def xor(x, y):
    return ''.join([_xormap[a, b] for a, b in zip(x, y)])


def print_binary(input):
    print(bin(input)[2:].zfill(len(a)))


def repetition_binary(binary, length):
    result = []
    for x in binary:
        result.append(x * length)
    return result


def split_binary(input, length, total_iteration):
    result = []
    for start in range(0, length * total_iteration, length):
        result.append(input[start:start + length])
    return result


def find_majority(votes):
    vote_count = Counter(votes)
    top_two = vote_count.most_common(2)
    if len(top_two) > 1 and top_two[0][1] == top_two[1][1]:
        # It is a tie
        return 0
    return top_two[0][0]


def generate_helper_data(key, input_file, repetition):
    i = 0
    result = []
    key_repeat = repetition_binary(key, repetition)
    for i in range(128):
        result.append(xor(key_repeat[i], input_file[i]))
    return result


def verify_helper(filename, original_key, helper_split, repetition):
    # file 2 as the base for reconstructing the key using helper data
    infile2 = open(filename).read().replace('\n', '')
    infile2 = infile2.replace(' ', '')
    infile2_split = split_binary(infile2, repetition, 128)

    # reconstructing the key
    reconstructed_key = ""
    for i in range(128):
        a = xor(helper_split[i], infile2_split[i])
        reconstructed_key += str(find_majority(a))

    print("difference : " + str(distance.hamming(original_key, reconstructed_key)))


def load_basefile(filename, repetition):
    infile1 = open(filename).read().replace('\n', '')
    infile1 = infile1.replace(' ', '')
    return split_binary(infile1, repetition, 128)
