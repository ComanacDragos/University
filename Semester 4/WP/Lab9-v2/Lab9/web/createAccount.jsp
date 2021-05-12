<%--
  Created by IntelliJ IDEA.
  User: Dragos
  Date: 5/12/2021
  Time: 6:35 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Create account</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="javascript/images.js"></script>
    <link href="main.css" rel="stylesheet" type="text/css">
</head>
<body>
<div class="column">
    <h1>Create account</h1>
    <label for="newUsername">Username</label>
    <input type="text" id="newUsername" name="newUsername"><br><br>
    <label for="newPassword">Password</label>
    <input type="password" id="newPassword" name="newPassword"><br><br>
    <label for="confirmPassword">Confirm password</label>
    <input type="password" id="confirmPassword" name="confirmPassword"><br><br>

    <nav>
        <button id="createAccountButton" onclick="createAccount()">Create account</button>
        <br>
        <br>
        <br>
        <form action="LoginController" method="get">
            <button>Go back to login</button>
        </form>
    </nav>
</div>
</body>
</html>
