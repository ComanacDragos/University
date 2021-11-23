var searchParams = new URLSearchParams(window.location.search)
var username = searchParams.get('username')

$.ajax({
    type : "GET",
    url : "http://localhost:3000/controller.php",
    data: {action: "getLoggedUser", username: username},					
        success: function(data, status) {
           if(!JSON.parse(data)){
                window.location.replace("index.html")
            }
        }
});

async function refreshNews(){
    $.ajax({
        type : "GET",
        url : "http://localhost:3000/controller.php",
        data: {
            action : 'getUserNews',
            username : username,
        },					
            success: function(data, status) {
                $("#newsContainer").html("")
                console.log(data)
                JSON.parse(data).forEach(element => {
                    //$("#newsContainer").append("<button class=\"news\">" + element['title'] + "</button>")    
                    $("#newsContainer").append(
                        $('<button/>',
                        {
                            text: element['title'],
                            class: 'news',
                            click: function(){
                                $.ajax(
                                    {
                                        type : "GET",
                                        url : "http://localhost:3000/controller.php",
                                        data : {
                                            action : 'getNewsWithTitle',
                                            title: $(this).text()
                                        },
                                        success: function(data, status){
                                            let news = JSON.parse(data)[0]
                                            $("#title").val(news['title'])
                                            $("#category").val(news['category'])
                                            $('#date').val(news['date'])
                                            $('#text').val(news['text'])
                                        }
                                    }
                                )

                            }
                        }
                        )    
                    )
                });
                refreshHandles()
            }
        });
}

$("#backToNews").click(
    (e)=>{
        e.preventDefault()
        window.location.replace("news.html?username=" + username)
    }
)

$("#addNewsButton").click(
    (e) =>{
        title = $("#title").val()
        category = $("#category").val()
        date = $("#date").val()
        text = $("#text").val()
        $.ajax({
            type : "GET",
            url : "http://localhost:3000/controller.php",
            data: {
                action : 'addNews',
                title : title , 
                username : username,
                category : category,
                date : date,
                text : text
            },					
                success: function(data, status) {
                    console.log(data)
                    
                    if(JSON.parse(data) === true){
                        //alert("News added")
                        refreshNews()
                    }
                    else
                        alert("Could not add news")
                }
            });
    }
)

$("#deleteNewsButton").click(
    (e)=>{
        $.ajax({
            type : "GET",
            url : "http://localhost:3000/controller.php",
            data: {
                action : 'deleteNews',
                title : $("#title").val() , 
                username : username,
            },					
                success: function(data, status) {
                    console.log(data)
                    data = JSON.parse(data)
                    if(data[0])
                        refreshNews()
                    else
                        alert(data[1])
                }
            });
    }
)

$("#updateNewsButton").click(
    (e)=>{
        $.ajax({
            type : "GET",
            url : "http://localhost:3000/controller.php",
            data: {
                action : 'updateNews',
                title : $("#title").val() , 
                username : username,
                category : $("#category").val(),
                date : $("#date").val(),
                text : $("#text").val()
            },					
                success: function(data, status) {
                    console.log(data)
                    data = JSON.parse(data)
                    if(data[0])
                        refreshNews()
                    else
                        alert(data[1])
                }
            });
    }
)

refreshNews()
$("#newsContainer").css("text-align", "center")

