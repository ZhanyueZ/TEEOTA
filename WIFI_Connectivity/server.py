from flask import Flask, send_file

app = Flask(__name__)

@app.route('/')
def download_file():
 file_path = 'C:/Users/89336/PycharmProjects/pythonProject1/text.txt'
 return send_file(file_path, as_attachment=True)


if __name__ == '__main__':
 app.run(host='0.0.0.0', port=80)