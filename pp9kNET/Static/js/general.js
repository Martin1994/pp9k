$(document).ready(function()
{
    if ($("#welcome-page").length > 0)
    {
        // Welcome page
        $(".new-game-div button").click(function()
        {
            $.ajax("newgame", { player1: "human", player2: "human"}, function(respond)
            {
                var gameid = respond.gameid;
                window.location.href="game?gameid=" + gameid;  
            }, "json");
        });
    }
});