$(document).ready(function(){
	$('#temperature-slider').inputSliderRange({
        "min": 0,
        "max": 80,
        "start": 10
      });

	$('#humidity-slider').inputSliderRange({
        "min": 0,
        "max": 80,
        "start": 10
      });

	$('#light-slider').inputSliderRange({
        "min": 0,
        "max": 80,
        "start": 10
      });

	$('#water-level-slider').inputSliderRange({
        "min": 0,
        "max": 80,
        "start": 10
      });
});

function update_control_values(){
	var temperature_val = $('#temperature-slider').val();
	var humidity_val = $('#humidity-slider').val();
	var light_intensity_val = $('#light-slider').val();
	var water_level_val = $('#water-level-slider').val();

	form_data = {
        'temperature': temperature_val,
        'humidity': humidity_val,
        'light_intensity': light_intensity_val,
        'water_level': water_level_val
    }
    form_data = JSON.stringify(form_data);
    console.log(form_data);

    $.putJSON("/control", form_data, function(data){
        console.log(data);
        if (data.code == "00") {
            notify_success();
        }
        else{
            notify_failure(data.msg);
        }
    });
}