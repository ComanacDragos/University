<%@ page import="webubb.domain.User" %><%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/12/2021
  Time: 1:40 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>All images</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="javascript/images.js"></script>
    <link href="main.css" rel="stylesheet" type="text/css">
</head>
<body>
<%! User user; %>
<%  user = (User) session.getAttribute("user");
    if (user != null) {
%>
<div class="column">
    <h1><%="Welcome " + user.getUsername()%></h1>
    <h2>All photos</h2>
    <form action="LoginController" method="get">
        <button>Logout</button>
    </form>
    <form action="PageController" method="get">
        <input type="hidden" name="page" value="images.jsp">
        <button>Browse my photos</button>
    </form>
    <br>
    <label for="noImages">Top liked images</label>
    <input type="text" id="noImages">
    <br>
    <button style="width: 50%" onclick="getAllImages('<%=user.getUsername()%>')">Get images</button>
    <br>
    <div class="column" id="images"></div>

    <script>
        getAllImages('<%=user.getUsername()%>')
    </script>
</div>
<%
    }
%>
</body>
</html>
