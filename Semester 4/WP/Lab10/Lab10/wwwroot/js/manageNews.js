function refreshNews(){
    $.ajax({
        type : "GET",
        url: "/Main/GetTitlesOfUser", 
        data: {},					
            success: function(data, status) {
                $("#newsContainer").html("")
                    data.forEach(title => {
                    $("#newsContainer").append(
                        $('<button/>',
                        {
                            text: title,
                            class: 'news',
                            click: function(){
                                $.ajax(
                                    {
                                        type : "GET",
                                        url: "/Main/GetNewsWithTitle", 
                                        data : {
                                            title: $(this).text()
                                        },
                                        success: function (data, status) {
                                            $("#title").val(data.title)
                                            $("#category").val(data.category)
                                            $('#date').val(data.date.split("T")[0])
                                            $('#text').val(data.text)
                                        }
                                    }
                                )

                            }
                        }
                        )    
                    )
                });
            }
        });    
}

$("#addNewsButton").click(
    (e) =>{
        title = $("#title").val()
        category = $("#category").val()
        date = $("#date").val()
        text = $("#text").val()
        $.ajax({
            type : "GET",
            url : "/Main/AddNews", 
            data: {
                title : title , 
                category : category,
                date : date,
                text : text
            },					
                success: function(data, status) {
                    $("#message").html(data)
                    refreshNews()
                }
            });
    }
)

$("#deleteNewsButton").click(
    (e) => {
        console.log()
        if (confirm("Are you sure you want to delete news?"))
            $.ajax({
                type : "GET",
                url : "/Main/DeleteNews", 
                data: {
                    title : $("#title").val(), 
                },					
                    success: function(data, status) {
                        $("#message").html(data)
                        refreshNews()
                    }
                });
    }
)

$("#updateNewsButton").click(
    (e)=>{
        $.ajax({
            type : "GET",
            url : "/Main/UpdateNews", 
            data: {
                title : $("#title").val() , 
                category : $("#category").val(),
                date : $("#date").val(),
                text : $("#text").val()
            },					
                success: function(data, status) {
                    $("#message").html(data)
                    refreshNews()
                }
            });
    }
)

refreshNews()

