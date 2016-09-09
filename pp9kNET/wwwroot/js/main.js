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