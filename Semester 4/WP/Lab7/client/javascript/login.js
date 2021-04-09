$("#loginButton").click(()=>{
    var user = $("#username").val()
    var psw= $("#password").val()
    $.ajax({
        type : "GET",
        url : "http://localhost:3000/Lab7/server/controller.php", 
        data: {action: "getUser", username : user , password : psw},					
            success: function(data, status) {
                console.log(data)
                if(JSON.parse(data))
                    window.location.replace("news.html?username=" + user)
                else
                    alert("Invalid credentials")
            }
        });
    }
  )

$("#createAccountButton").click(
    ()=>{
        window.location.replace("createAccount.html")
    }
)

$("#viewNews").click(
    ()=>{
        window.location.replace("news.html")
    }
)

