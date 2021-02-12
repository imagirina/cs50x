#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Maxnumber of candidates an election can have
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes; //representing the number of votes the candidate has
}
candidate;

// Array of candidates
candidate candidates[MAX]; //global array of candidates, where each element is itself a candidate.

// Number of candidates
int candidate_count; //the program sets a global variable candidate_count representing the number of candidates in the election

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    //the program copies command-line arguments into the array candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // the program asks the user to type in the number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    // the program lets every voter type in a vote, calling the vote function on each candidate voted for.
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

bool vote(string name)
{
    // If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote.
    // The vote function in this case should return true to indicate a successful ballot.
    // If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function
    // should return false to indicate an invalid ballot.

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            //printf("Found %s has %i votes\n", candidates[i].name, candidates[i].votes);
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    /*
    printf("Array: ");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s - %i | ", candidates[i].name, candidates[i].votes);
    }
    printf("\n");
    */
    int temp_votes;
    string temp_name;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes > candidates[i].votes)
            {
                temp_votes = candidates[i].votes;
                temp_name = candidates[i].name;
                candidates[i].votes = candidates[j].votes;
                candidates[i].name = candidates[j].name;
                candidates[j].votes = temp_votes;
                candidates[j].name = temp_name;
            }
        }
    }
    /*
    printf("Sorted: ");
    for (int i = 0; i < candidate_count; i++) {
         printf("%s - %i | ", candidates[i].name, candidates[i].votes);
    }
    printf("\n");
    */
    int max_vote = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}