var searchParams = new URLSearchParams(window.location.search)
var username = searchParams.get('username')

function refreshNews(){
    $.ajax({
        type : "GET",
        url : "http://localhost:3000/Lab7/server/controller.php", 
        data: {
            action : 'getUserNews',
            username : username,
        },					
            success: function(data, status) {
                $("#newsContainer").html("")
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
                                        url : "http://localhost:3000/Lab7/server/controller.php", 
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
            url : "http://localhost:3000/Lab7/server/controller.php", 
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
        console.log($("#title").val())
    }
)

refreshNews()
$("#newsContainer").css("text-align", "center")

