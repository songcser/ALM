package com.prolambda.model;

public enum BuildResult {

	SUCCESS("was successful"),
    FAILURE("failed"),
    ERROR("have error"),
    UNSTABLE("was unstable"),
    ABORTED("was aborted"),
    NOT_BUILT("was not built"),
    FIXED("was fixed"),
	WARNING("have Warning");

	private String humanResult;

    private BuildResult(String displayName) {
        this.humanResult = displayName;
    }
    
    public String getHumanResult() {
        return humanResult;
    }
}
