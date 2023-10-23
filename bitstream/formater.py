import re

#Format existing .RBT file

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

#print("Unwrapped bitstream file.")
#print(merged_binary_array)

def convert_int(list):
    ret = []
    for element in list:
        ret.append(int(element))
    return ret
#JUST DO OPERATIONS ON PRE-GENERATED BITSTREAM

filename = "SITE_DEMO.RBT"

with open(filename,'r') as f:
    line = f.read();

#extract data for each cell

hh,gh,gg,hg = [], [], [], []

for i in range(643,1921,71):
    for j in range(0,8):
        hh.append(line[i+j])
        
for i in range(651,1929,71):
    for j in range(0,8):
        gh.append(line[i+j])

for i in range(1929,3207,71):
    for j in range(0,8):
        gg.append(line[i+j])

for i in range(1921,3199,71):
    for j in range(0,8):
        hg.append(line[i+j])

hh = convert_int(hh)
gh = convert_int(gh)
gg = convert_int(gg)
hg = convert_int(hg)

fh,eh,dh,fg,eg,dg = [], [], [], [], [], []

for i in range(660,1938,71):
    for j in range(0,8):
        fh.append(line[i+j])

for i in range(668,1946,71):
    for j in range(0,8):
        eh.append(line[i+j])

for i in range(676,1954,71):
    for j in range(0,8):
        dh.append(line[i+j])

for i in range(1938,3216,71):
    for j in range(0,8):
        fg.append(line[i+j])

for i in range(1946,3224,71):
    for j in range(0,8):
        eg.append(line[i+j])

for i in range(1954,3232,71):
    for j in range(0,8):
        dg.append(line[i+j])

fh = convert_int(fh)
eh = convert_int(eh)
dh = convert_int(dh)
fg = convert_int(fg)
eg = convert_int(eg)
dg = convert_int(dg)

ch,bh,ah,cg,bg,ag = [], [], [], [], [], []

for i in range(685,1963,71):
    for j in range(0,8):
        ch.append(line[i+j])

for i in range(693,1971,71):
    for j in range(0,8):
        bh.append(line[i+j])

for i in range(701,1979,71):
    for j in range(0,8):
        ah.append(line[i+j])

for i in range(1963,3241,71):
    for j in range(0,8):
        cg.append(line[i+j])

for i in range(1971,3249,71):
    for j in range(0,8):
        bg.append(line[i+j])

for i in range(1979,3257,71):
    for j in range(0,8):
        ag.append(line[i+j])

ch = convert_int(ch)
bh = convert_int(bh)
ah = convert_int(ah)
cg = convert_int(cg)
bg = convert_int(bg)
ag = convert_int(ag)

#Write 144 bit matrices to output file for C++ to 
#setup CLBs

with open("Parse_out.txt",'w') as f:
    for bit in hh:
        f.write(str(bit))
    f.write("\n")
    for bit in gh:
        f.write(str(bit))
    f.write("\n")
    for bit in fh:
        f.write(str(bit))
    f.write("\n")
    for bit in eh:
        f.write(str(bit))    
    f.write("\n")
    for bit in dh:
        f.write(str(bit))
    f.write("\n")
    for bit in ch:
        f.write(str(bit))
    f.write("\n")
    for bit in bh:
        f.write(str(bit))
    f.write("\n")
    for bit in ah:
        f.write(str(bit))
    f.write("\n")
    for bit in hg:
        f.write(str(bit))
    f.write("\n")
    for bit in gg:
        f.write(str(bit))
    f.write("\n")
    for bit in fg:
        f.write(str(bit))
    f.write("\n")
    for bit in eg:
        f.write(str(bit))
    f.write("\n")
    for bit in dg:
        f.write(str(bit))
    f.write("\n")
    for bit in cg:
        f.write(str(bit))
    f.write("\n")
    for bit in bg:
        f.write(str(bit))
    f.write("\n")
    for bit in ag:
        f.write(str(bit))