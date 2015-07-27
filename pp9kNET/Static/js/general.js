$(document).ready(function()
{
    if ($("#welcome-page").length > 0)
    {
        // Welcome page
        $(".new-game-div button").click(function()
        {
            alert("123");
            $.ajax("newgame", { player1: "human", player2: "human"}, function(respond)
            {
                var gameid = respond.gameid;
                alert(gameid);
                window.location.href="game?gameid=" + gameid;  
            }, "json");
        });
    }
});