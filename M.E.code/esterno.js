var step = 1;
var url_topic_folder = "https://dl.dropboxusercontent.com/u/18897774/Progetti/MM3_v4_sources/";
var cml_jsawesome = document.getElementsByClassName("cml jsawesome");
var array_imgs = getRandomImageArray();
var lineValues = new Object();
var oldTime = 0;
var docs = new Array();
var judgments = new Array();
var log = new Array();
var passo = 1;

$(document).ready(function() {

    log.push({
        msg : "start task",
        time : $.now()
    });

    strTrec7 = importRemoteFile("https://dl.dropboxusercontent.com/u/18897774/Progetti/MM3_v4_sources/topics/topics.351-400");
    strTrec8 = importRemoteFile("https://dl.dropboxusercontent.com/u/18897774/Progetti/MM3_v4_sources/topics/topics.401-450");

    arrayTrec7 = strTrec7.split("<top>");
    arrayTrec8 = strTrec8.split("<top>");

    showEnd(false);

    // Setting the first istruction
    $(".well > p ").html(importRemoteFile("https://dl.dropboxusercontent.com/u/18897774/MagnitudeEstimationExperiments/instruction/instructions_4_part_1.txt"));

    id_topic = $("#topic").attr( "value" );
    //console.log("Id topic: " + id_topic);
	//console.log("sotto");
	//console.log(id_topic.attr( "value" ));

	//console.log("Arrivo")
	
	//console.log(url_topic_folder + "topics.xml")
	
	//console.log("id_topic: " + id_topic)
	
    doc_H = getDocH(url_topic_folder + "topics.xml", id_topic);
    doc_N = getDocN(url_topic_folder + "topics.xml", id_topic);
	
	//console.log(doc_H)

    pos_doc_H = getPos(doc_H);
    pos_doc_N = getPos(doc_N);

    console.log("Doc N: " + doc_N + ", in position:  " + (pos_doc_N+1));
    console.log("Doc H: " + doc_H + ", in position: " + (pos_doc_H+1));

    $("#topicText").html(populateTopics(id_topic));

    // Import all documents
    for (var i = 0; i < 8; i++) {
        // console.log(url_topic_folder + "docs/" + $("#doc_" + (i + 1)).val());
        docs[i] = formatWell(importRemoteFile(url_topic_folder + "docs/" + $("#doc_" + (i + 1)).val()));
    };

    // console.log(docs);

    question_obj = getQuestion("https://dl.dropboxusercontent.com/u/18897774/Progetti/MM3_v4_sources/topics.xml", id_topic);

    // console.log(question_obj);

    $("#question").text(question_obj.question);
    $("#l_0").text(question_obj.answers[0]);
    $("#l_1").text(question_obj.answers[1]);
    $("#l_2").text(question_obj.answers[2]);
    $("#l_3").text(question_obj.answers[3]);

    for (var i = 0; i < 8; i++) {
        judgments.push(new Object());
        judgments[i].doc =$("#doc_" + (i + 1)).val();
    }

    cml_jsawesome[0].style.overflow = "hidden";

    updateStep();
    $("#lineVal").focus();

    $("#btnBack").click(function(evt) {
        if (step > 1) {
            step--;
            if (step > 5)
                passo++;

            updateStep();
        }
        event.preventDefault();
    });

    $("#btnNext").click(function(evt) {
        if (step < 13 && verifyStep()) {
            step++;

            if (step > 5)
                passo++;

            updateStep();
        }
        event.preventDefault();
    });

    $("#btnWarning").click(function(evt) {
        step = 5;
        updateStep();
        event.preventDefault();
    });

    $("#relVal").keypress(function(event) {
        console.log(isNumberOrDot(event));
        if (!isNumberOrDot(event)) {
            event.preventDefault();
        }
    });

    $("#lineVal").keypress(function(event) {
        console.log(isNumberOrDot(event));
        if (!isNumberOrDot(event)) {
            event.preventDefault();
        }
    });

    // $("input").keypress(function(evt) {
    // var charCode = evt.charCode || evt.keyCode;
    // if (charCode == 13) {//Enter key's keycode
    // return false;
    // }
    // });

    $("#line").click(function(evt) {
        // console.log("Click");
        errore();
        event.preventDefault();
    });

    $("#lineVal").keyup(function(evt) {
        switch(array_imgs[step - 1]) {
        case "s":
            lineValues.s = parseFloat($("#lineVal").val());
            break;
        case "m":
            lineValues.m = parseFloat($("#lineVal").val());
            break;
        case "l":
            lineValues.l = parseFloat($("#lineVal").val());
            break;
        }

        if (isNaN(lineValues.l)) {
            lineValues.l = "";
        }
        if (isNaN(lineValues.m)) {
            lineValues.m = "";
        }
        if (isNaN(lineValues.s)) {
            lineValues.s = "";
        }
    });
});

function verifyStep() {
    switch (step) {
    case 1:
    case 2:
    case 3:
        if (validateRegex("" + $("#lineVal").val())) {
            switch(array_imgs[step - 1]) {
            case "s":
                lineValues.s = parseFloat($("#lineVal").val());
                log.push({
                    msg : "short line evalued: " + lineValues.s,
                    time : $.now()
                });
                break;
            case "m":
                lineValues.m = parseFloat($("#lineVal").val());
                log.push({
                    msg : "medium line evalued: " + lineValues.m,
                    time : $.now()
                });
                break;
            case "l":
                lineValues.l = parseFloat($("#lineVal").val());
                log.push({
                    msg : "long line evalued: " + lineValues.l,
                    time : $.now()
                });
                break;
            }
            $("#lineVal").focus();
            $("#lineErr").slideUp("slow");

            return true;
        } else {
            errore();
            return false;
        }
        break;
    case 4:

        // Get POS for first control
        var pos = -1;
        if ($("#a_0").is(":checked") == true)
            pos = 0;
        if ($("#a_1").is(":checked") == true)
            pos = 1;
        if ($("#a_2").is(":checked") == true)
            pos = 2;
        if ($("#a_3").is(":checked") == true)
            pos = 3;

        // console.log("Answer control: " + answerControl(pos));
        // console.log("Line control: " + lineControl());
        // console.log(lineValues);

        if (answerControl(pos) && lineControl()) {
            return true;
        } else {
            blockTask();
            return false;
        }

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:

        // window.scrollTo(0, 0);
        return verifyDoc();
        break;
    }
}

function verifyDoc() {
    // console.log("Validate Regex: " + validateRegex($("#relVal").val()));
    // console.log("Linea Val: " + $("#comVal").val().length);

    if (validateRegex($("#relVal").val()) && $("#comVal").val().length > 0) {
        $("#relVarErr").slideUp("slow");
        $("#comValErr").slideUp("slow");

        // console.log("Passo il test allo step " + step);

        var d = new Date();
        s = {
            msg : "change doc",
            doc : (step - 4),
            rel : $("#relVal").val(),
            comm : $("#comVal").val(),
            step : passo,
            time : $.now()
        };
        // console.log(s);
        log.push(s);

    } else {

        if (!validateRegex($("#relVal").val())) {
            $("#relVarErr").slideDown("slow");
            var d = new Date();
            s = {
                msg : "test not pass: bad relevance value",
                doc : (step - 4),
                rel : $("#relVal").val(),
                comm : $("#comVal").val(),
                step : passo,
                time : $.now()
            };
            // console.log(s);
            log.push(s);

        } else {
            $("#relVarErr").slideUp("slow");
        }

        if (!($("#comVal").val().length > 0)) {
            $("#comValErr").slideDown("slow");
            var d = new Date();
            s = {
                msg : "test not pass: bad comment value",
                doc : (step - 4),
                rel : $("#relVal").val(),
                comm : $("#comVal").val(),
                step : passo,
                time : $.now()
            };
            // console.log(s);
            log.push(s);

        } else {
            $("#comValErr").slideUp("slow");

        }
        // console.log("NON Passo il test allo step" + step);
        return false;
    }

    judgments[(step - 5)].rel = $("#relVal").val();
    judgments[(step - 5)].com = $("#comVal").val();

    $("#relVal").val("");
    $("#comVal").val("");

    newTime = $.now();

    diff = (newTime - oldTime) / 1000;

    if (judgments[(step - 5)].time != null) {
        judgments[(step - 5)].time = judgments[(step - 5)].time + diff;
    } else {
        judgments[(step - 5)].time = diff;
    }
    oldTime = newTime;
    // console.log(judgments);

    window.scrollTo(0, 0);
    return true;
}

function answerControl(pos) {
    if (pos == question_obj.correct)
        return true;
    return false;
}

function lineControl() {
    // console.log(lineValues.s + " - " + lineValues.m + " - " + lineValues.l);
    if (lineValues.s < lineValues.m && lineValues.m < lineValues.l)
        return true;
    return false;
}

function updateStep() {
    // console.log("Update. Step = " + step);
    hideAll();

    switch (step) {
    case 1:
        showLines();
        $("#btnBack").hide();
        expandInstructions();
        break;
    case 2:
    case 3:
        $("#btnBack").show();
        showLines();
        break;

    case 4:
        $("#topicBox").show();
        $("#questionBox").show();
        $("#btnBox").show();
        break;
    case 5:
        oldTime = $.now();

        // Hide back button
        $("#btnBack").hide();

        $("body").scrollTop(0);
        // Setting the second istruction

        injectInstructions(importRemoteFile("https://dl.dropboxusercontent.com/u/18897774/MagnitudeEstimationExperiments/instruction/instructions_4_part_2.txt"));
        expandInstructions();
        // $(".well > p ").html(importRemoteFile("https://dl.dropboxusercontent.com/u/18897774/MagnitudeEstimationExperiments/instruction/instructions_4_part_2.txt"));
        // $(".well").slideDown("slow");

        showDocs();
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        oldTime = $.now();
        //console.log(oldTime);
        $("#btnBack").show();
        showDocs();
        break;
    case 13:
        if (finalControl()) {
            step = 14;
            updateStep();
        } else {

            $("#warningBox").show();
        }
        break;
    case 14:

        setResult(aggregaLog());
        showEnd(true);
        $("#endBox").show();
    }
}

function showLines() {
    $("#lineBox").show();
    $("#btnBox").show();

    switch(array_imgs[step - 1]) {
    case "s":
        $("#lineVal").val(lineValues.s);
        break;
    case "m":
        $("#lineVal").val(lineValues.m);
        break;
    case "l":
        $("#lineVal").val(lineValues.l);
        break;
    }
    $('#line').removeClass("s m l").addClass(array_imgs[step - 1]);
}

function showDocs() {
    $('#doc_title').html("Document " + (step - 4) + " of 8");
    $('#doc_text').html(docs[(step - 5)]);

    if (judgments[step - 5].com != null) {
        $("#comVal").val(judgments[step - 5].com);
    }
    if (judgments[step - 5].rel != null) {
        $("#relVal").val(judgments[step - 5].rel);
    }
    $("#btnBox").show();
    $("#topicBox").show();
    $("#documentBox").show();
    // $("#topicBox").focus();
}

function errore() {
    $("#lineErr").slideDown("slow");
}

function blockTask() {
    hideAll();
    closeInstructions();
    $("#errorBox").show();
}

function hideAll() {
    $("#documentBox").hide();
    $("#questionBox").hide();
    $("#lineBox").hide();
    $("#endBox").hide();
    $("#topicBox").hide();
    $("#errorBox").hide();
    $("#btnBox").hide();
    $("#warningBox").hide();
}

function validateRegex(str) {
    var reU = /^(null|(?!0*[.]0*$|[.]0*$|0*$)\d+[.]?\d{0,}$)/;
    return reU.test(str);
}

function finalControl() {

    // console.log("Stampo fine");
    // console.log(log);

    // console.log("Il documento H è: " + doc_H + ", si trova in posizione: " + (pos_doc_H + 1) + " e il suo giudizio è " + judgments[pos_doc_H].rel);    
    // console.log("Il documento N è: " + doc_N + ", si trova in posizione: " + (pos_doc_N + 1) + " e il suo giudizio è " + judgments[pos_doc_N].rel);
    if (parseInt(judgments[pos_doc_N].rel) >= parseInt(judgments[pos_doc_H].rel)) {

        str = "final control: test relevance FAILED: rel(H)= " + judgments[pos_doc_H].rel + ", rel(N)= " + judgments[pos_doc_N].rel;

        // console.log(str);

        log.push({
            msg : str,
            time : $.now()
        });

        return false;
    } else {
        // console.log("final control: test relevance PASSED");
    }

    var quanti = 0;

    var soglia = 20;

    for (var i = 0; i < 8; i++) {
        if (judgments[i].time < soglia) {
            quanti++;
        }
    }

    if (quanti > 2) {

        str = "final control: test times FAILED. " + quanti + " document times < " + soglia;

        // console.log(str);
        log.push({
            msg : str,
            time : $.now()
        });

        return false;
    } else {
        str = "final control: test times PASSED. " + quanti + " document times < " + soglia;
        // console.log(str);

        log.push({
            msg : str,
            time : $.now()
        });

        return true;
    }
}

function getPos(doc) {
    for (var i = 0; i < 8; i++) {
        if ($("#doc_" + (i + 1)).val() == doc) {
            return i;
        }
    };
    alert('ERROR IN DATA');
    return null;
}

/**
 formatWell -> migliora leggermente la formattazione dei document
 */
function formatWell(str) {
    // str = str.replace(/\s\n/gm, " ");
    // str = str.replace(/\n\n{2,}/gm, "" + '\n');

    str = str.replace(/^(?:[\t ]*(?:\r?\n|\r))+/gm, '\n');

    return str;
}

/**
 populateTopics
 */
function populateTopics(num_topic) {
    num = parseInt(num_topic);
    cTopic = "";
    if (num > 350 && num <= 400) {
        console.log("cerco in trec 7 ");
        cTopic = arrayTrec7[num - 350].replace(/(\r\n|\n|\r)/gm, " ");
    } else {
        if (num > 400 && num <= 450) {
            console.log("cerco in trec 8 ");
            cTopic = arrayTrec8[num - 400].replace(/(\r\n|\n|\r)/gm, " ");
        } else {
            console.log("PROBLEMA GRAVE CON GLI INDICI");
        }
    }
    console.log("Current topic: " + cTopic);
    rest = cTopic;
    number = rest.split("<title>")[0];
    rest = rest.split("<title>")[1];
    control = number.charAt(16) + number.charAt(17) + number.charAt(18);
    if (num == parseInt(control)) {
        console.log("Controllo incrociato: OK");
    } else {
        console.log("INDEX PROBLEM!!!!");
    }
    title = rest.split("<desc>")[0];
    rest = cTopic.split("<desc>")[1];
    desc = rest.split("<narr>")[0];
    rest = cTopic.split("<narr>")[1];
    narr = rest.split("</top>")[0];
    return "<B>TITLE:</B>" + title + "</br><B>DESCRIPTION:</B>" + desc.replace("Description:", "") + "</br><B>NARRATIVE:</B>" + narr.replace("Narrative:", "");
};

function aggregaLog() {
    var res = new Array();
    res.push(getUA());
    res.push(lineValues);
    res.push(judgments);
    res.push(log);

    return JSON.stringify(res);

}

