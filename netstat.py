import subprocess
p1 = subprocess.Popen(["netstat", "-a"], stdout=subprocess.PIPE)
p2 = subprocess.Popen(["grep", "ESTABLISHED"], stdin=p1.stdout, stdout=subprocess.PIPE)
p1.stdout.close()  # Allow p1 to receive a SIGPIPE if p2 exits.
output,err = p2.communicate()
f = open("netstat.txt", "w")
f.write(output)
f.close();
