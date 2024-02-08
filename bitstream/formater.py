import re

def convert_int_list(data, start, end, step, length):
    result = []
    for i in range(start, end, step):
        for j in range(0, length):
            result.append(int(data[i + j]))
    return result

def write_to_file(output_file, *bit_lists):
    try:
        with open(output_file, 'r'):
            # File exists, open in append mode
            mode = 'a'
    except FileNotFoundError:
        # File doesn't exist, open in write mode
        mode = 'w'

    with open(output_file, mode) as f:
        for bit_list in bit_lists:
            for bit in bit_list:
                f.write(str(bit))
            f.write("\n")


def main():
    # Format existing .RBT file
    filename = "TEST1.RBT"
    with open(filename, 'r') as file:
        lines = file.read()

    pattern = re.compile(r'0([01]{71})111')
    matches = pattern.findall(lines)

    columns = []
    # Extract 160 columns
    for i in range(160):
        if i < len(matches):
            columns.append(matches[i])
        else:
            columns.append("0" * 71)

    merged_binary_array = ''.join(columns)

    # JUST DO OPERATIONS ON PRE-GENERATED BITSTREAM

    filename = "SITE_DEMO.RBT"

    with open(filename, 'r') as f:
        line = f.read()

    # Extract data for each cell
    hh = convert_int_list(line, 643, 1921, 71, 8)
    gh = convert_int_list(line, 651, 1929, 71, 8)
    gg = convert_int_list(line, 1921, 3199, 71, 8)
    hg = convert_int_list(line, 1929, 3207, 71, 8)

    fh = convert_int_list(line, 660, 1938, 71, 8)
    eh = convert_int_list(line, 668, 1946, 71, 8)
    dh = convert_int_list(line, 676, 1954, 71, 8)
    fg = convert_int_list(line, 1938, 3216, 71, 8)
    eg = convert_int_list(line, 1946, 3224, 71, 8)
    dg = convert_int_list(line, 1954, 3232, 71, 8)

    ch = convert_int_list(line, 685, 1963, 71, 8)
    bh = convert_int_list(line, 693, 1971, 71, 8)
    ah = convert_int_list(line, 701, 1979, 71, 8)
    cg = convert_int_list(line, 1963, 3241, 71, 8)
    bg = convert_int_list(line, 1971, 3249, 71, 8)
    ag = convert_int_list(line, 1979, 3257, 71, 8)

    hf = convert_int_list(line, 3341, 4619, 71, 8)
    gf = convert_int_list(line, 3349, 4627, 71, 8)
    ge = convert_int_list(line, 4627, 5905, 71, 8)
    he = convert_int_list(line, 4619, 5897, 71, 8)

    ff = convert_int_list(line, 3358, 4636, 71, 8)
    ef = convert_int_list(line, 3366, 4644, 71, 8)
    df = convert_int_list(line, 3374, 4652, 71, 8)
    fe = convert_int_list(line, 4636, 5914, 71, 8)
    ee = convert_int_list(line, 4644, 5922, 71, 8)
    de = convert_int_list(line, 4652, 5930, 71, 8)

    cf = convert_int_list(line, 3383, 4661, 71, 8)
    bf = convert_int_list(line, 3391, 4669, 71, 8)
    af = convert_int_list(line, 3399, 4677, 71, 8)
    ce = convert_int_list(line, 4661, 5939, 71, 8)
    be = convert_int_list(line, 4669, 5947, 71, 8)
    ae = convert_int_list(line, 4677, 5955, 71, 8)

    # Write 176 bit matrices to output file for C++ to setup CLBs
    write_to_file("Parse_out.txt", hh,gh,fh,eh,dh,ch,bh,ah)
    write_to_file("Parse_out.txt", hg,gg,fg,eg,dg,cg,bg,ag)
    write_to_file("Parse_out.txt", hf,gf,ff,ef,df,cf,bf,af)
    write_to_file("Parse_out.txt", he,ge,fe,ee,de,ce,be,ae)


if __name__ == "__main__":
    # This block will be executed only if the script is run as the main program
    main()