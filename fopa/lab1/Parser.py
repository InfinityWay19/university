from bs4 import*
import requests
def parse():
    url = 'https://pypi.org/project/bs4/'
    page = requests.get(url)
    print(page.status_code)
    soup = BeautifulSoup(page.text, "html.parser")
    block = soup.find_all('div', class_='project-description')
    description=''
    for data in block:
        if data.find('p'):
            description = data.text
    print(description)