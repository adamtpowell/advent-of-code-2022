import sys

def completely_within(ranges): # The bug is here.

    set1 = set(range(ranges[0][0], ranges[0][1] + 1))
    set2 = set(range(ranges[1][0], ranges[1][1] + 1))

    intersection = set1 & set2

    valid = len(intersection) != 0

    return valid

    # range1 = ranges[0]
    # range2 = ranges[1]

    # if range1[0] >= range2[0] and range1[1] <= range2[1]: # range1 is contained in the range of range 2
    #     return True
    # elif range2[0] >= range1[0] and range2[1] <= range1[1]: # Range 2 is inside range 1
    #     return True

    # return False

total = 0

for line in sys.stdin:
    sections = line.strip().split(",")

    ranges = [(int(section.split('-')[0]), int(section.split('-')[1])) for section in sections]

    if completely_within(ranges):
        total += 1

print("Total", total)
