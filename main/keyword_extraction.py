# This Python file uses the following encoding: utf-8
import jieba.analyse
import encodings;
def keyword_extraction(text,path):
    keywords = jieba.analyse.extract_tags(text, topK=6, withWeight=False)
    with open(path + "/answers.txt","w",encoding="UTF-8") as file:
        file.truncate(0)
        for i in range(0,6):
            file.write(str(keywords[i]) + "\r\n")
# if__name__ == "__main__":
#     pass
