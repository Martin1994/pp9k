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
        /** @type WebSocket */
        this._ws = null;
    };

    Game.prototype.JoinGame = function (id, name, password, role) {
        var that = this;

        location.hash = id;
        $("#game-page #game-title").html(name);

        // Connect to the game
        var wsprotocol = location.protocol === "http:" ? "ws:" : "wss:";
        var wspath = location.pathname + "game/" + id;
        var wshost = location.host;
        var wsurl = wsprotocol + "//" + wshost + wspath;
        this._ws = new WebSocket(wsurl);
        this._ws.onmessage = function (e) {
            var command = JSON.parse(e.data);
            that.Respond(command);
        };

        if (role !== "observer") {
            this.Request({
                action: "authorize",
                password: password || ""
            });
        }
    };

    Game.prototype.Request = function (data) {
        this._ws.send(JSON.stringify(data));
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
            return "img/Chess_" + type.substr(0, 1) + (side === "white" ? "l" : "d") + "t45.svg";
        };
    };

    return Game;
})();