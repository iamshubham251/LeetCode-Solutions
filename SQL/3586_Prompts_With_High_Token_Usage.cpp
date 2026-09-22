WITH cte AS (
    SELECT
        user_id,
        tokens,
        COUNT(1) OVER(PARTITION BY user_id) AS prompt_count,
        ROUND(AVG(tokens) OVER(PARTITION BY user_id), 2) AS avg_tokens
    FROM prompts
)
SELECT DISTINCT
    user_id, prompt_count, avg_tokens
FROM cte
WHERE prompt_count > 2 AND tokens > avg_tokens
ORDER BY avg_tokens DESC , user_id ASC;
