window.Hall = (function () {
    "use strict";

    var FORM_TYPE = {
        NONE: 0,
        JOIN: 1,
        CREATE: 2
    };

    /**
     * Controls behaviour of game hall. (create/join game etc.)
     * @constructor
     */
    var Hall = function () {
        this._activeForm = FORM_TYPE.NONE;

        this.ApplyBinding();
    };

    Hall.prototype.ApplyBinding = function () {
        var that = this;

        $("#hall-page #new-game-button").click(function (e) {
            that.SelectForm(FORM_TYPE.CREATE);
        });

        $("#hall-page #join-game-button").click(function (e) {
            that.SelectForm(FORM_TYPE.JOIN);
        });

        $("#hall-page #new-game-confirm").click(function (e) {
            var name = $("#hall-page #game-name").val();
            var password = $("#hall-page #game-password").val();
            var role = $("#hall-page #play-as").val();
            $.post("game", {
                black: $("#hall-page #player-type-black").val(),
                name: name,
                password: password,
                white: $("#hall-page #player-type-white").val()
            }, function (data) {
                window.game.JoinGame(data.id, data.name, password, role);
            }).fail(function (xhr, status, error) {
                that.alert(JSON.parse(xhr.responseText).message);
            });
        });

        $("#hall-page #join-game-confirm").click(function (e) {
            var gameid = $("#hall-page #gameid").val();
            var password = $("#hall-page #join-game-password").val();
            var role = $("#hall-page #join-as").val();
            $.get("game/" + gameid, {}, function (data) {
                window.game.JoinGame(data.id, data.name, password, role);
            }).fail(function (xhr, status, error) {
                that.alert(JSON.parse(xhr.responseText).message);
            });
        });

        $("#hall-page #join-as").change(function (e) {
            var role = $(this).val();
            if (role === "observer") {
                $("#hall-page #join-game-password-option").slideUp();
            } else {
                $("#hall-page #join-game-password-option").slideDown();
            }
        });
    };

    /**
     * Show hall page
     */
    Hall.prototype.Show = function () {
        $('#hall-page').show();
    };

    /**
     * Hide hall page
     */
    Hall.prototype.Hide = function () {
        $('#hall-page').hide();
    };

    Hall.prototype.alert = function (text) {
        alert(text);
    };

    Hall.prototype.SelectForm = function (formType) {
        if (this._activeForm !== formType) {
            if (this._activeForm) {
                $("#hall-page .game-options").slideUp();
            }
            if (formType === FORM_TYPE.JOIN) {
                $("#hall-page #join-game-options").slideDown();
                $("#hall-page #join-game-button").removeClass("disabled");
                $("#hall-page #new-game-button").addClass("disabled");
            } else if (formType === FORM_TYPE.CREATE) {
                $("#hall-page #new-game-options").slideDown();
                $("#hall-page #new-game-button").removeClass("disabled");
                $("#hall-page #join-game-button").addClass("disabled");
            } else {
                $("#hall-page #new-game-button").addClass("disabled");
                $("#hall-page #join-game-button").addClass("disabled");
            }
            this._activeForm = formType;
        }
    };

    return Hall;
})();
