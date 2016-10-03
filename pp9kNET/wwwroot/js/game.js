window.Game = (function () {

    "use strict";

    var MESSAGE_TYPE = {
        MESSAGE: 0,
        ERROR: 1
    };

    var BOARD_WIDTH = 8;

    var Piece = function (type, side) {
        this.type = type;
        this.side = side;
    };

    Piece.prototype._imageMap = {
        King: "k",
        Queen: "q",
        Rook: "r",
        Knight: "n",
        Bishop: "b",
        Pawn: "p"
    };

    Piece.prototype.GetImage = function () {
        var typeStr = this._imageMap[this.type];
        if (!typeStr) {
            return "";
        }
        return "img/Chess_" + typeStr + (this.side === "White" ? "l" : "d") + "t45.svg";
    };

    var GameBoard = function () {
        this.board = [];
        for (var i = 0; i < BOARD_WIDTH; i++) {
            var column = [];
            for (var j = 0; j < BOARD_WIDTH; j++) {
                column.push(null);
            }
            this.board.push(column);
        }
    };

    GameBoard.prototype.GetPiece = function (x, y) {
        return this.board[x][y];
    };

    GameBoard.prototype.SetPiece = function (x, y, piece) {
        this.board[x][y] = piece;
        $(".board .grid[x=" + x + "][y=" + y + "]").html(piece.type == "Blank" ? "" : "<img src=\"" + piece.GetImage() + "\" />");
    };

    GameBoard.prototype.Clear = function () {
        $(".board .grid").html();
        for (var i = 0; i < BOARD_WIDTH; i++) {
            for (var j = 0; j < BOARD_WIDTH; j++) {
                this.board[i][j] = null;
            }
        }
    };

    /**
     * Controls behaviour of game board
     */
    var Game = function () {
        /** @type {Hall} */
        this.hall = null;
        this._role = "";
        this._authorized = false;
        this.selectedPiece = null;
        /** @type {WebSocket} */
        this._ws = null;
        this._wsPendingMessages = [];
        this._board = new GameBoard();
        this._turn = "white";

        this.ApplyBinding();
    };

    Game.prototype.ApplyBinding = function () {
        var that = this;

        $("#game-page .board .grid").click(function (e) {
            if (!that._authorized || that._turn.toLowerCase() !== that._role) {
                return;
            }

            var isEmpty = !$(this).html();
            var thisPiece = {
                x: $(this).attr("x"),
                y: $(this).attr("y")
            };

            if (that._selectedPiece) {
                // Move a piece to an empty cell
                that.Request({
                    action: "move",
                    from: {
                        x: that._selectedPiece.x,
                        y: that._selectedPiece.y
                    },
                    to: {
                        x: thisPiece.x,
                        y: thisPiece.y
                    }
                });
                // Deselect
                that._selectedPiece = null;
                $("#game-page .board .grid").removeClass("blink");
            } else if (!isEmpty) {
                // Change the select piece
                $("#game-page .board .grid").removeClass("blink");
                if (that._board.GetPiece(thisPiece.x, thisPiece.y).side.toLowerCase() === that._role) {
                    that._selectedPiece = thisPiece;
                    $("#game-page .board .grid[x=" + thisPiece.x + "][y=" + thisPiece.y + "]").addClass("blink");
                } else {
                    that._selectedPiece = null;
                }
            }
        });
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
        this._authorized = false;
        if (role !== "observer") {
            this.Request({
                action: "authorize",
                password: password || ""
            });
        }
        this.Request({
            action: "init"
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

                case "update_board":
                    this.SetBoard(commandContent);
                    break;

                case "update_turn":
                    this.SetTurn(commandContent);
                    break;

                case "authorize":
                    this._authorized = true;
                    $("#game-page .button-area").fadeIn();
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
     */
    Game.prototype.SetBoard = function (board, refresh) {
        for (var i = 0; i < board.length; i++) {
            var change = board[i];
            var piece = new Piece(change.type, change.side);
            this._board.SetPiece(change.x, change.y, piece);
        }
    };

    Game.prototype.SetTurn = function (turn) {
        // Update resign button
        if (turn.toLowerCase() === this._role) {
            $("#game-page #resign-button").removeAttr("disabled");
        } else {
            $("#game-page #resign-button").attr("disabled", "");
        }

        // Set turn colour
        $("#game-page .turn").removeClass(this._turn.toLowerCase());
        $("#game-page .turn").addClass(turn.toLowerCase());

        this._turn = turn;

        // Deselect
        this._selectedPiece = null;
        $("#game-page .board .grid").removeClass("blink");
    };

    Game.prototype.ShowMessage = function (message) {
        this.PushMessage(message, MESSAGE_TYPE.MESSAGE);
    };

    Game.prototype.ShowError = function (message) {
        this.PushMessage(message, MESSAGE_TYPE.ERROR);
    };

    Game.prototype.PushMessage = function (message, type) {
        var typeClass = type === MESSAGE_TYPE.MESSAGE ? "message" : "error";
        $("#game-page .message-area").append("<div class=\"message\"><span class=\"" + typeClass + "\">" + message + "</span></div>");
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