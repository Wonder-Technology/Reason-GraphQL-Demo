# project
Demo实现了用户注册和登录功能， 包括jest测试。

前后端使用GraphQL，以及前端使用Apollo搭配Reason-React显示GraphQL查询到的数据。

后端封装好所有GraphQL操作，通过graphql_schema.json暴露给前端，在这里面配置了前端可以查询哪些字段，前端自己组合查询，需要前后端开发人员都学习GraphQL，并需要前端人员知道需要哪些字段。

目前我的做法是把数据库查询(Query)操作暴露出去，所有Mutation由后端执行，不让前端直接操作数据库，还是通过接口进行。

业务逻辑主要使用Most.Js流控制，有需要可以学习下Most.js

需要用户配置数据库信息，具体查看 create database and table

# Getting started

```js 
npm install -g cyarn --registry=https://registry.npm.taobao.org

npm config set puppeteer_download_host=https://npm.taobao.org/mirrors

cyarn install 
```


# create database and table

```js
change  ServerConfig.re -> database config(set user and password and database)

create database: your setted database

create table userLogin: get sql from UserLoginTableTool.re

create table userInfo: get sql from UserInfoTableTool.re
```

# build project

```js
npm run bsb:watch

npm run webpack:dev
```

# in another tab

```js
npm run start

then you can open localhost:8888
```

# GraphQL setting 
read graphql_schema.json
