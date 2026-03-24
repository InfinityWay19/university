import requests
from bs4 import BeautifulSoup

url = "https://countrymeters.info/ru/World"

headers = {
    "User-Agent": "Mozilla/5.0"
}

response = requests.get(url, headers=headers)

soup = BeautifulSoup(response.text, "html.parser")

total_births = soup.find(id="cp1").text
births_year = soup.find(id="cp6").text
deaths_year = soup.find(id="cp8").text

print("\n       [ WORLD BIRTH RATE ]")
print("+--------------------------------+")
print("|Total births:", total_births, "    |")
print("+--------------------------------+")
print("|Births this year:", births_year, "   |")
print("+--------------------------------+")
print("|Deaths this year:", deaths_year, "   |")
print("+--------------------------------+")
