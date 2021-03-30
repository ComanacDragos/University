var noCol = 5
var noRow = 5

function generateRow(content){
    var row = ""
    for(var j=0;j<noCol;j+=1)
        row += "<td>" + content + "</td>"
    row = "<td><button>-</button></td>" + row + "<td><button>+</button></td>"
    return "<tr>" + row + "</tr>"
}

function setHandles(){
    $("button").unbind()
    $("input").unbind()
    $("button").click(handleButton)
    $("input").keyup(handleInput)
}

function handleButton(){
    if($(this).text() == "+"){
        $(this).parent().parent().after(generateRow('<input type="text"></input>'))
        setHandles()
    }
    else{
        $(this).parent().parent().remove()
        $("table").css('top', (parseFloat($("table").css("top")) + $("tr").height()) + 'px')
    }
}

function handleInput(event){
    if(event.key == "Enter"){
        var row = $(this).parent().parent().children()
        
        var count = 0
        for(var i=1;i<row.length-1;i+=1)
            if(row[i].firstChild.value != "")
                count += 1

        if(count == noCol)
            for(var i=1;i<row.length-1;i+=1)
                row[i].innerHTML = row[i].firstChild.value 
            
    }
}

for(var i=0;i<noRow;i+=1)
    $("table").append(generateRow(Math.floor(90*Math.random() + 10)))


$("button").click(handleButton)
