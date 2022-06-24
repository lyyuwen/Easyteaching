# This Python file uses the following encoding: utf-8
import requests
import base64

def text_recognize(filename):

    host = 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=U47G8lUAYMcd4bxdz8v7dW5c&client_secret=ufybrM2bsXTloB8K3fAfTT2LUbPhTsWt'
    response = requests.get(host)
    response = response.json()

    request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/accurate_basic"

    f = open(filename + ".jpg", 'rb')
    img = base64.b64encode(f.read())

    params = {"image":img}
    access_token = response["access_token"]   #"24.2cf53f0001e037a53a00f8f11dd2d365.2592000.1650690744.282335-25834980"
    request_url = request_url + "?access_token=" + access_token
    headers = {'content-type': 'application/x-www-form-urlencoded'}
    response = requests.post(request_url, data=params, headers=headers)
    if response:
        response = response.json()
        response = response["words_result"]
        text = ""
        for i in response:
            text = text + i["words"]
        print(text)
        with open(filename + ".txt","w",encoding="UTF-8") as resultfile:
            resultfile.write(text)

# if__name__ == "__main__":
#     pass
