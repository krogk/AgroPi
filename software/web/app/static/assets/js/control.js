$(document).ready(function(){
	$('#temperature-slider').inputSliderRange({
        "min": -40,
        "max": 125,
        "start": 10
      });

	$('#humidity-slider').inputSliderRange({
        "min": 0,
        "max": 100,
        "start": 10
      });

	$('#light-slider').inputSliderRange({
        "min": 0,
        "max": 120000,
        "start": 10
      });

	$('#water-level-slider').inputSliderRange({
        "min": 0,
        "max": 80,
        "start": 10
      });
    $('#tvoc-slider').inputSliderRange({
        "min": 0,
        "max": 60000,
        "start": 10
      });

    $('#eco2-slider').inputSliderRange({
        "min": 0,
        "max": 60000,
        "start": 10
      });
});

function update_control_values(){
	var temperature_val = $('#temperature-slider').val();
	var humidity_val = $('#humidity-slider').val();
	var light_intensity_val = $('#light-slider').val();
	var water_level_val = $('#water-level-slider').val();
    var tvoc_val = $('#tvoc-slider').val();
    var eco2_val = $('#eco2-slider').val();

	form_data = {
        'temperature': temperature_val,
        'humidity': humidity_val,
        'light_intensity': light_intensity_val,
        'water_level': water_level_val,
        'tvoc': tvoc_val,
        'eco2': eco2_val
    }
    form_data = JSON.stringify(form_data);
    console.log(form_data);
    $('#update-control-button').attr('disabled', true);

    $.putJSON("/control", form_data, function(data){
        console.log(data);
        if (data.code == "00") {
            notify_success("Values updated");
            $('#update-control-button').attr('disabled', false);
        }
        else{
            notify_failure(data.msg);
        }
    });
}