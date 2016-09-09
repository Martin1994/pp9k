window.Hall = (function () {
    'use strict';

    /**
     * Controls behaviour of game hall. (create/join game etc.)
     * @constructor
     */
    var Hall = function () {};

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

    return Hall;
})();
