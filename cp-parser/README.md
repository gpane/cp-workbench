HTTP server that receives requests from Competitive Companion and generates txt files.

1. Download the [Competitive Companion](https://chrome.google.com/webstore/detail/competitive-companion/cjnmckjndlpiamhfimnnjmnckgghkjbl?hl=en-US) chrome extension.
2. Add the port used by this server as a custom port in Competitive Companion settings. (Default is 4567 but can be changed by calling Spark.port(...).)
3. Set the desired destination for the input/expected-output txt files in Main.java.
4. Run `./gradlew run` to run. (Possibly need to `./gradlew build` first.)
