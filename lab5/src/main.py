#!/usr/bin/env python
# -*- coding: utf-8 -*-
from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello_unix():
   return 'Куда мы без UNIX?'

if __name__ == '__main__':
    app.run(debug=True,host='0.0.0.0')