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

    filename = "SITE_DEMO.RBT"

    with open(filename, 'r') as f:
        line = f.read()

    # Extract data for each cell
    hh = convert_int_list(line, 643, 1921, 71, 8)
    gh = convert_int_list(line, 651, 1929, 71, 8)
    fh = convert_int_list(line, 660, 1938, 71, 8)
    eh = convert_int_list(line, 668, 1946, 71, 8)
    dh = convert_int_list(line, 676, 1954, 71, 8)
    ch = convert_int_list(line, 685, 1963, 71, 8)
    bh = convert_int_list(line, 693, 1971, 71, 8)
    ah = convert_int_list(line, 701, 1979, 71, 8)

    hg = convert_int_list(line, 1929, 3207, 71, 8)
    gg = convert_int_list(line, 1921, 3199, 71, 8)
    fg = convert_int_list(line, 1938, 3216, 71, 8)
    eg = convert_int_list(line, 1946, 3224, 71, 8)
    dg = convert_int_list(line, 1954, 3232, 71, 8)
    cg = convert_int_list(line, 1963, 3241, 71, 8)
    bg = convert_int_list(line, 1971, 3249, 71, 8)
    ag = convert_int_list(line, 1979, 3257, 71, 8)

    hf = convert_int_list(line, 3341, 4619, 71, 8)
    gf = convert_int_list(line, 3349, 4627, 71, 8)
    ff = convert_int_list(line, 3358, 4636, 71, 8)
    ef = convert_int_list(line, 3366, 4644, 71, 8)
    df = convert_int_list(line, 3374, 4652, 71, 8)
    cf = convert_int_list(line, 3383, 4661, 71, 8)
    bf = convert_int_list(line, 3391, 4669, 71, 8)
    af = convert_int_list(line, 3399, 4677, 71, 8)

    ge = convert_int_list(line, 4627, 5905, 71, 8)
    he = convert_int_list(line, 4619, 5897, 71, 8)
    fe = convert_int_list(line, 4636, 5914, 71, 8)
    ee = convert_int_list(line, 4644, 5922, 71, 8)
    de = convert_int_list(line, 4652, 5930, 71, 8)
    ce = convert_int_list(line, 4661, 5939, 71, 8)
    be = convert_int_list(line, 4669, 5947, 71, 8)
    ae = convert_int_list(line, 4677, 5955, 71, 8)

    hd = convert_int_list(line, 5897, 7175, 71, 8)
    gd = convert_int_list(line, 5905, 7183, 71, 8)
    fd = convert_int_list(line, 5914, 7192, 71, 8)
    ed = convert_int_list(line, 5922, 7200, 71, 8)
    dd = convert_int_list(line, 5930, 7208, 71, 8)
    cd = convert_int_list(line, 5939, 7217, 71, 8)
    bd = convert_int_list(line, 5947, 7225, 71, 8)
    ad = convert_int_list(line, 5955, 7233, 71, 8)

    hc = convert_int_list(line, 7317, 8595, 71, 8)
    gc = convert_int_list(line, 7325, 8603, 71, 8)
    fc = convert_int_list(line, 7334, 8612, 71, 8)
    ec = convert_int_list(line, 7342, 8620, 71, 8)
    dc = convert_int_list(line, 7350, 8628, 71, 8)
    cc = convert_int_list(line, 7359, 8637, 71, 8)
    bc = convert_int_list(line, 7367, 8645, 71, 8)
    ac = convert_int_list(line, 7375, 8653, 71, 8)

    hb = convert_int_list(line, 8595, 9873, 71, 8)
    gb = convert_int_list(line, 8603, 9881, 71, 8)
    fb = convert_int_list(line, 8612, 9890, 71, 8)
    eb = convert_int_list(line, 8620, 9898, 71, 8)
    db = convert_int_list(line, 8628, 9906, 71, 8)
    cb = convert_int_list(line, 8637, 9915, 71, 8)
    bb = convert_int_list(line, 8645, 9923, 71, 8)
    ab = convert_int_list(line, 8653, 9931, 71, 8)

    ha = convert_int_list(line, 9873, 11151, 71, 8)
    ga = convert_int_list(line, 9881, 11159, 71, 8)
    fa = convert_int_list(line, 9890, 11168, 71, 8)
    ea = convert_int_list(line, 9898, 11176, 71, 8)
    da = convert_int_list(line, 9906, 11184, 71, 8)
    ca = convert_int_list(line, 9915, 11193, 71, 8)
    ba = convert_int_list(line, 9923, 11201, 71, 8)
    aa = convert_int_list(line, 9931, 11209, 71, 8)

    # Write 176 bit matrices to output file for C++ to setup CLBs
    write_to_file("Parse_out.txt", hh,gh,fh,eh,dh,ch,bh,ah)
    write_to_file("Parse_out.txt", hg,gg,fg,eg,dg,cg,bg,ag)
    write_to_file("Parse_out.txt", hf,gf,ff,ef,df,cf,bf,af)
    write_to_file("Parse_out.txt", he,ge,fe,ee,de,ce,be,ae)
    write_to_file("Parse_out.txt", hd,gd,fd,ed,dd,cd,bd,ad)
    write_to_file("Parse_out.txt", hc,gc,fc,ec,dc,cc,bc,ac)
    write_to_file("Parse_out.txt", hb,gb,fb,eb,db,cb,bb,ab)
    write_to_file("Parse_out.txt", ha,ga,fa,ea,da,ca,ba,aa)

if __name__ == "__main__":
    # This block will be executed only if the script is run as the main program
    main()
