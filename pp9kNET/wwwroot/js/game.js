window.Game = (function () {

    "use strict";

    var MESSAGE_TYPE = {
        MESSAGE: 0,
        ERROR: 1
    };

    /**
     * Controls behaviour of game board
     */
    var Game = function () {
        /** @type {WebSocket} */
        this._ws = null;
        /** @type {Hall} */
        this.hall = null;
        this._role = "";
        this._wsPendingMessages = [];
    };

    Game.prototype.JoinGame = function (id, name, password, role) {
        var that = this;

        this.Show();
        this.hall.Hide();

        location.hash = id;
        $("#game-page #game-title").html(name);

        // Connect to the game
        var wsprotocol = location.protocol === "http:" ? "ws:" : "wss:";
        var wspath = location.pathname + "game/" + id;
        var wshost = location.host;
        var wsurl = wsprotocol + "//" + wshost + wspath;
        this._ws = new WebSocket(wsurl);
        this._wsPendingMessages = [];
        this._ws.onmessage = function (e) {
            var command = JSON.parse(e.data);
            that.Respond(command);
        };
        this._ws.onopen = function (e) {
            for (var i = 0; i < that._wsPendingMessages.length; i++) {
                that._ws.send(that._wsPendingMessages[i]);
            }
            that._wsPendingMessages = [];
        };

        this._role = role;
        if (role !== "observer") {
            this.Request({
                action: "authorize",
                password: password || ""
            });
        }
        this.Request({
            action: "get_board"
        });
    };

    Game.prototype.Request = function (data) {
        switch (this._ws.readyState) {
            case WebSocket.CONNECTING:
                this._wsPendingMessages.push(JSON.stringify(data));
                break;

            case WebSocket.OPEN:
                this._ws.send(JSON.stringify(data));
                break;

            default:
                this.ShowError("WebSocket is closed.")
        }
    };

    Game.prototype.Respond = function (command) {
        for (var commandName in command) {
            if (!command.hasOwnProperty(commandName)) {
                continue;
            }
            var commandContent = command[commandName];
            switch (commandName) {
                case "message":
                    this.ShowMessage(commandContent);
                    break;

                case "error":
                    this.ShowError(commandContent);
                    break;

                case "board":
                    this.SetBoard(commandContent, false);
                    break;

                case "update_board":
                    this.SetBoard(commandContent, true);
                    break;

                default:
                    this.ShowError("Invalid command: " + commandName);
                    break;
            }
        };
    };

    /**
     * Set the game board
     * @param {Array} board - board information
     * @param {boolean} refresh - if true, the board will be cleard before set the incomming board data; if false, only the position contained in the incomming board data will be updated
     */
    Game.prototype.SetBoard = function (board, refresh) {
        if (refresh) {
            $(".board .grid").html();
        }
        for (var i = 0; i < board.length; i++) {
            for (var j = 0; j < board[0].length; j++) {
                var change = board[i][j];
                $(".board .grid[x=" + i + "][y=" + j + "]").html(change.type == "Blank" ? "" : "<img src=\"" + this.GetPieceImage(change.type, change.side) + "\" />");
            }
        }
    };

    Game.prototype.ShowMessage = function (message) {
        this.PushMessage(message, MESSAGE_TYPE.MESSAGE);
    };

    Game.prototype.ShowError = function (message) {
        this.PushMessage(message, MESSAGE_TYPE.ERROR);
    };

    Game.prototype.PushMessage = function (message, type) {
        alert((type === MESSAGE_TYPE.MESSAGE ? "Message: " : "Error: ") + message);
    };

    Game.prototype.GetPieceImage = function (type, side) {
        return "img/Chess_" + type.substr(0, 1).toLowerCase() + (side === "White" ? "l" : "d") + "t45.svg";
    };

    /**
     * Show game page
     */
    Game.prototype.Show = function () {
        $('#game-page').show();
    };

    /**
     * Hide game page
     */
    Game.prototype.Hide = function () {
        $('#game-page').hide();
    };

    return Game;
})();