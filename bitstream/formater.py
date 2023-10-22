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

hh = []
gh = []
gg = []
hg = []

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
print(hh)
#print_rect(gh)
#print_rect(gg)
#print_rect(hg) 
