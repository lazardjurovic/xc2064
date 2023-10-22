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

#JUST DO OPERATIONS ON PRE-GENERATED BITSTREAM

filename = "SITE_DEMO.RBT"

with open(filename,'r') as f:
    line = f.read();

cell = []

for i in range(643,1921,71):
    for j in range(0,8):
        print(i+j,line[i+j])
        cell.append(line[i+j])
        
print(cell)