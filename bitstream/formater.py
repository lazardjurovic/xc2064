import re

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

with open("OUT.RBT",'w') as out:
    for col in columns:
        out.write(col)
        out.write("\n")

merged_binary_array = ''.join(columns)

print("Unwrapped bitstream file.")
print(merged_binary_array)



