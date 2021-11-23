$("#createAccountButton").click(
    ()=>{
        $.ajax({
            type : "GET",
            url : "http://localhost:3000/controller.php",
            data: {
                action: "registerUser", 
                username : $("#newUsername").val(), 
                password : $("#newPassword").val(),
                confirmPassword: $("#confirmPassword").val()
            },					
                success: function(data, status) {
                    alert(JSON.parse(data))
                }
            });  
    }
)

$("#backToLogin").click(
    ()=>{
        window.location.replace("index.html")
    }
)