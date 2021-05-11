<%@ page import="webubb.domain.User" %><%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/11/2021
  Time: 1:40 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Images</title>

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

        <input type="file"  accept="image/*" name="image" id="file"  onchange="loadFile(event)" style="display: none;">
        <button style="width: 20%"><label for="file" style="cursor: pointer;">Upload Image</label></button>

        <br>
        <div class="column" id="userPhotos"></div>
        <script>
            const loadFile = function (event) {
                addImage( <%= user.getId() %>, event.target.files[0])
            };
        </script>

        <script defer>
            getImagesOfUser(<%=user.getId()%>, '<%=user.getUsername()%>')
        </script>
    </div>
<%
    }
%>
</body>
</html>
