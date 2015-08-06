function respond_handler(respond)
{
    if (!respond.success)
    {
        alert(respond.error);
        return;
    }

    for (var i in respond.actions)
    {
        var action = respond.actions[i];
        switch (action.action)
        {
            case "update-board":
                for (var j in action.param)
                {
                    var change = action.param[j];
                    update_piece(change);
                }
                break;

            case "update-turn":
                if (action.param == "White")
                {
                    $(".grid.turn").addClass("white");
                    $(".grid.turn").removeClass("black");
                }
                else
                {
                    $(".grid.turn").addClass("black");
                    $(".grid.turn").removeClass("white");
                }
                break;
        }
    }
}

function update_piece(change)
{
    var type;
    switch (change.type)
    {
        case "Blank":
            type = "blank";
            break;

        case "King":
            type = "k";
            break;

        case "Queen":
            type = "q";
            break;

        case "Bishop":
            type = "b";
            break;

        case "Rook":
            type = "r";
            break;

        case "Knight":
            type = "n";
            break;

        case "Pawn":
            type = "p";
            break;

    }
    var color = change.side == "White" ? "l" : "d";
    var img = "/static/img/Chess_" + type + color + "t45.svg";
    $(".board .grid[x=" + change.x + "][y=" + change.y + "]").html(type == "blank" ? "" : "<img src=\"" + img + "\" />");
}

function init_game_board(game_id) {
    $(".title .gameid").html("#" + game_id);

    $.post("command/refresh", { gameid: game_id }, respond_handler, "json");

    $(".board .grid").click(function (e)
    {
        if ($(this).find("img").length > 0) {
            // Valid piece
            if ($(".board .grid.blink").length > 0) {
                // Already selected some piece.
                if ($(".board .grid.blink")[0] == $(this)[0]) {
                    // Same piece. Cancel it.
                    $(this).removeClass("blink");
                }
                else {
                    // Different piece. Make move.
                    var from = $(".board .grid.blink");
                    var to = $(this);
                    from.removeClass("blink");
                    $.post("command/move", { "gameid": game_id, "from-x": from.attr("x"), "from-y": from.attr("y"), "to-x": to.attr("x"), "to-y": to.attr("y") }, respond_handler, "json");
                }
            }
            else {
                // Haven't selected any piece.
                $(this).addClass("blink");
            }
        }
        else {
            // Blank
            if ($(".board .grid.blink").length > 0) {
                // Already selected some piece. Make move.
                var from = $(".board .grid.blink");
                var to = $(this);
                from.removeClass("blink");
                $.post("command/move", { "gameid": game_id, "from-x": from.attr("x"), "from-y": from.attr("y"), "to-x": to.attr("x"), "to-y": to.attr("y") }, respond_handler, "json");
            }
        }
    });

    window.addEventListener("message", function (e) {
        eval("respond_handler(" + e.data + ");");
    });

    $.post("token", { gameid: game_id }, function (respond)
    {
        $("iframe.comet").attr("src", "http://" + window.location.hostname + ":86/CDPortal.php?token=" + respond.token);
    }, "json");
}

$(document).ready(function ()
{
    if ($("#welcome-page").length > 0)
    {
        // Welcome page
        $(".new-game-div button").click(function()
        {
            $.post("newgame", { player1: "human", player2: "human"}, function(respond)
            {
                window.location.href = "game#" + respond.gameid;
            }, "json");
        });
    }

    if ($("#game-page").length > 0)
    {
        init_game_board(window.location.hash.substr(1));
    }
});