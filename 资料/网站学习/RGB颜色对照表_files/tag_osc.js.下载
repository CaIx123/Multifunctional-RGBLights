$(function () {
    $.get('https://www.oschina.net/action/ajax/get_tool_ad', function (res) {
        if (res && res.status === 1) {
            var showHTML = '';
            var adId = res.ad_id || '';
            var ident = res.ident || '';
            var href = res.href || '#';
            var html = res.html || '';
            var js = res.js || '';
            var detail = res.detail || '';
            var img = res.img || '';
            var width = res.width || '';
            var height = res.height || '';
            if (html != '' && html.trim().length > 0) {
                showHTML = '<div name="' + ident + '" data-traceid="' + adId + '" data-tracepid="' + ident + '">' + html + '</div>';
            } else {
                showHTML = '<a data-traceid="' + adId + '" data-tracepid="' + ident + '" href="' + href + '" target="_blank" title="' + detail + '">\n' +
                    '  <img src="' + img + '" width="' + width + '" height="' + height + '">\n' +
                    '</a>';
                if (js != '' && js.trim().length > 0) {
                    showHTML += js;
                }
            }
            if (showHTML != '') {
                $('.ad-wrap').html(showHTML);
            }
        }

        traceAd();
    });

    // 广告PV/Click上报
    function traceAd() {
        // PV
        var adEls = $('[data-traceid][data-tracepid]');
        if (adEls && adEls.length > 0) {
            adEls.each(function (index, _adEl) {
                var adEl = $(_adEl);
                var traceid = adEl.data('traceid');
                var tracepid = adEl.data('tracepid');
                if (traceid && tracepid) {
                    // PV
                    $.get("https://www.oschina.net/action/trace/record?e=pv&aid=" + traceid + "&p=" + tracepid);
                }
            });
        }

        // Click
        $(document).on('click', '[data-traceid][data-tracepid]', function () {
            var adEl = $(this);
            var traceid = adEl.data('traceid');
            var tracepid = adEl.data('tracepid');
            if (traceid && tracepid) {
                // Click
                $.get("https://www.oschina.net/action/trace/record?e=click&aid=" + traceid + "&p=" + tracepid);
            }
        });
    }
});
