fname = input("Please enter a file name:")
f = open(fname, "r")
i=1
line = " "
check = 0
while(line):
	line = f.readline()
	for j in range(0, len(line)):
		if(j>=80):
			print("Line over 80 chars:" + str(i))
			check = 1
		if(line[j] == "\n" and line[j-1] == " "):
			print("Endline space : " + str(i))
			check = 1
	i = i + 1
if(check == 0):
	print("/*----------------------------*/")
	print("	    File clean!")
	print("/*----------------------------*/")


f.close()
