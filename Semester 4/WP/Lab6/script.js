var noCol = 5
var noRow = 5

function generateRow(content){
    var row = ""
    for(var j=0;j<noCol;j+=1)
        row += "<td>" + content + "</td>"
    row = "<td><button>-</button></td>" + row + "<td><button>+</button></td>"
    return row
}

function setHandles(){
    $("button").unbind()
    $("input").unbind()
    $("button").click(handleButton)
    $("input").keyup(handleInput)
}

function handleButton(){
    if($(this).text() == "+"){
        $(this).parent().parent().after("<tr>" + generateRow('<input type="text"></input>') + "</tr>")
        setHandles()
    }
    else
        $(this).parent().parent().remove()
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
                row[i].innerHTML = "<td>" + row[i].firstChild.value + "</td>"
            
    }
}

for(var i=0;i<noRow;i+=1){
    row = generateRow(Math.floor(90*Math.random() + 10))
    $("table").append("<tr>" + row + "</tr>")
}

$("button").click(handleButton)
