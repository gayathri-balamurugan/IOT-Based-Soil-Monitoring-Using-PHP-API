<?php
if(isset($_GET['soil']))
{
    $soil= $_GET['soil'];
    echo "soil value received :" .$soil;
}
else
{
 echo "soil value not recevied";
}
?>