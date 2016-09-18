window.App = {
    Hall: null,
    Game: null
};

(function () {
    $(document).ready(function () {
        var hall = new Hall();

        var startAtGame = window.location.hash.length > 0;

        if (startAtGame) {

        } else {
            hall.Show();
        }
    });
})();

function test () {
    $.ajax('game', {
        method: 'post',
        data: {},
        contentType: 'application/x-www-form-urlencoded; charset=UTF-8',
        success: function (data) {
            window.ws = new WebSocket("ws://localhost:50369/game/" + data.id);
            ws.onmessage = function (e) {
                console.debug(JSON.parse(e.data));
            };
            ws.onopen = function () {
                ws.send(JSON.stringify({ action: 'get_board' }));
            };
        }
    });
}