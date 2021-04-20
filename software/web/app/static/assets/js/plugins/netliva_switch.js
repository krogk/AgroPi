(function ($) {

	$.fn.netlivaSwitch = function(settings, val)
	{
		let $input = this;
		let first = false;
		let $container, $label;
		let returnValue = null;

		if (typeof settings === "string")
		{
			if (typeof val === "undefined")
			{
				returnValue = settings;
				settings = {}
			}
			else
			{
				settings = {[settings] : val}
			}
		}
		if (typeof settings !== 'object')
			settings = {};

		if	($input.data("netlivaSwitch") === "initalized")
		{
			$container = $input.parent();
			$label = $input.next();
		}
		else
		{
			first = true;
			$container = $("<div/>");
			$label = $("<label/>");

			var id = $input.attr("id");
			if (!id)
			{
				id = "netliva-switch-"+ (Math.floor(Math.random() * 10000000000) + 1);
				$input.attr('id', id);
			}
			$label.attr("for",id);

			$container.addClass("netliva-switch");
			$input.clone().appendTo($container);
			$label.appendTo($container);
			$input.replaceWith($container);
			$input = $container.find("input");
			$input.on("change", function () {
				$(this).trigger( "netlivaSwitch.change", [ $(this).prop("checked"), $(this) ] );
			});

			settings = $.extend( {
				 "active-text": $input.data("active-text") ? $input.data("active-text") : null,
				 "passive-text": $input.data("passive-text") ? $input.data("passive-text") : null,
				 "width": $input.data("width") ? $input.data("width") : null,
				 "active-color": $input.data("active-color") ? $input.data("active-color") : null,
				 "passive-color": $input.data("passive-color") ? $input.data("passive-color") : null,
			 }, settings );

			if (typeof settings.width === 'undefined' || !settings.width)
			{
				var textsize = 3;

				if (settings["active-text"] && settings["active-text"].length > textsize)
					textsize = settings["active-text"].length;
				if (settings["passive-text"] && settings["passive-text"].length > textsize)
					textsize = settings["passive-text"].length;

				settings.width = (textsize*0.55 + 2.5)+"em";
			}
			else if (typeof settings.width !== 'string')
			{
				settings.width += "px";
			}

			$input.data("netlivaSwitch", "initalized");
		}

		$.each(settings, function (key, val) {
			if (val !== null)
			{
				switch(key) {
					case "active-text":
					case "passive-text":
						$label.attr("data-"+key, val);
						break;
					case "active-color":
					case "passive-color":
						if (val.substr(0,1) !== "#") val = 'var(--'+val+')';
						$label.css('--switch-'+key, val);
						break;
					case "disable":
					case "disabled":
						$input.prop("disabled", val);
						break;
					case "val":
					case "chacked":
					case "state":
						$input.prop("checked", val);
						break;
					case "width":
						$label.css("width", val);
						break;
				}
			}
		});

		if (returnValue)
		{
			switch(returnValue) {
				case "checked":
				case "state":
					return $input.prop("checked");
				case "disabled":
					return $input.prop("disabled");
				default:
					return undefined;
			}
		}

		return $input;

	};

	function init()
	{

		$("[netliva-switch]").each(function () {
			if ($(this).attr("netliva-switch") !== "OK")
			{
				$(this).attr("netliva-switch", "OK");
				$(this).netlivaSwitch({});
			}
		});
	}

	$(document).ajaxComplete(init);
	init();


})(jQuery);

