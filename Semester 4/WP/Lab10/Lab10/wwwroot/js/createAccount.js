$("#createAccountButton").click(
    ()=>{
        $.ajax({
            type : "GET",
            url: "/Main/SaveAccount", 
            data: {
                username : $("#newUsername").val(), 
                password : $("#newPassword").val(),
                confirmPassword: $("#confirmPassword").val()
            },					
                success: function(data, status) {
                    $("#message").html(data)
                }
            });  
    }
)