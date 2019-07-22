## Getting started

npm install -g cyarn --registry=https://registry.npm.taobao.org

npm config set puppeteer_download_host=https://npm.taobao.org/mirrors

cyarn install 


# create database and table
change  ServerConfig.re -> database config(set user and password and database)

create database: your setted database

create table userLogin: get sql from UserLoginTableTool.re

create table userInfo: get sql from UserInfoTableTool.re

# build project
npm run bsb:watch

npm run webpack:dev

# in another tab
npm run start

then you can open localhost:8888