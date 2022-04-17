package parser;

import org.json.JSONArray;
import org.json.JSONObject;
import spark.Spark;

import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Main {
    // SET THIS TO WHERE INPUT/OUTPUT FILES SHOULD BE CREATED
    //static final Path root = Paths.get("/Users/gianluca/Dropbox/contests/kotlin");
    static final Path root = Paths.get("../samples");

    public static void main(String[] args) {
        Spark.post("/*", (request, response) -> {
            System.out.println("RECEIVED REQUEST: ");
            System.out.println(request.body());

            // Clear out the directory of old tests
            Files.list(root)
                    .filter(f -> f.getFileName().toString().startsWith("input")
                            || f.getFileName().toString().startsWith("output")
                            || f.getFileName().toString().equals("format")
                            || f.getFileName().toString().startsWith("expected-output"))
                    .forEach(f -> {
                        try {
                            System.out.println("Deleting " + f.getFileName());
                            Files.delete(f);
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    });

            // Write new tests
            JSONArray tests = new JSONObject(request.body()).getJSONArray("tests");
            for (int i = 0; i < tests.length(); i++) {
                System.out.printf("Creating test file %d\n", i);
                try (FileWriter inputFw = new FileWriter(root + "/input" + i)) {
                    inputFw.write((String) tests.getJSONObject(i).get("input"));
                }
                try (FileWriter outputFw = new FileWriter(root + "/expected-output" + i)) {
                    outputFw.write((String) tests.getJSONObject(i).get("output"));
                }
            }
            return response;
        });
    }
}
